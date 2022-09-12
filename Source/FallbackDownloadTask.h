#pragma once
#include <JuceHeader.h>

struct FallbackDownloadTask : public URL::DownloadTask,
    public Thread
{
    FallbackDownloadTask(std::unique_ptr<FileOutputStream> outputStreamToUse,
        size_t bufferSizeToUse,
        std::unique_ptr<WebInputStream> streamToUse,
        URL::DownloadTask::Listener* listenerToUse)
        : Thread("DownloadTask thread"),
        fileStream(std::move(outputStreamToUse)),
        stream(std::move(streamToUse)),
        bufferSize(bufferSizeToUse),
        buffer(bufferSize),
        listener(listenerToUse)
    {
        jassert(fileStream != nullptr);
        jassert(stream != nullptr);

        targetLocation = fileStream->getFile();
        contentLength = stream->getTotalLength();
        httpCode = stream->getStatusCode();

        startThread();
    }

    ~FallbackDownloadTask() override
    {
        signalThreadShouldExit();
        stream->cancel();
        waitForThreadToExit(-1);
    }

    //==============================================================================
    void run() override
    {
        while (!(stream->isExhausted() || stream->isError() || threadShouldExit()))
        {
            if (listener != nullptr)
                listener->progress(this, downloaded, contentLength);

            auto max = (int)jmin((int64)bufferSize, contentLength < 0 ? std::numeric_limits<int64>::max()
                : static_cast<int64> (contentLength - downloaded));

            auto actual = stream->read(buffer.get(), max);

            if (actual < 0 || threadShouldExit() || stream->isError())
                break;

            if (!fileStream->write(buffer.get(), static_cast<size_t> (actual)))
            {
                error = true;
                break;
            }

            downloaded += actual;

            if (downloaded == contentLength)
                break;
        }

        fileStream.reset();

        if (threadShouldExit() || stream->isError())
            error = true;

        if (contentLength > 0 && downloaded < contentLength)
            error = true;

        finished = true;

        if (listener != nullptr && !threadShouldExit())
            listener->finished(this, !error);
    }

    //==============================================================================
    std::unique_ptr<FileOutputStream> fileStream;
    const std::unique_ptr<WebInputStream> stream;
    const size_t bufferSize;
    HeapBlock<char> buffer;
    URL::DownloadTask::Listener* const listener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FallbackDownloadTask)
};