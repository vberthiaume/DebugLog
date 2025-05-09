#include <JuceHeader.h>

//TODO: this needs to be OS dependent, and this needs to be in a shared file
static constexpr auto kSharedMemoryMapFilepath { "/tmp/ProPhatSharedMemory" };
static constexpr auto kMaxDebugEntries { 2048 };

struct DebugLogEntry
{
    juce::int64 timeSinceLastCall {};
    juce::int64 processCallDuration {};
    int         curEffect {};
};

struct DebugLog
{
    DebugLogEntry   log[kMaxDebugEntries];
    volatile size_t logHead {};
};

inline void printDebugLogEntry (DebugLogEntry& logEntry)
{
    std::cout << "timeSinceLastCall: " << juce::String (logEntry.timeSinceLastCall)
              << ", processCallDuration: " << juce::String (logEntry.processCallDuration)
              << ", Effect: " << logEntry.curEffect << std::endl;
}

//==============================================================================
int main (int argc, char* argv[])
{
    std::cout << "ProPhat Debug Log Reader" << std::endl;

    //Map file to memory..
    auto                   mmFile = juce::File (kSharedMemoryMapFilepath);
    juce::MemoryMappedFile logDebugMapping (mmFile, juce::MemoryMappedFile::readOnly, false);
    DebugLog*              m_pLogDebug = (DebugLog*) logDebugMapping.getData();
    if (! m_pLogDebug)
    {
        std::cerr << "\n\nError! Failed to map file " << kSharedMemoryMapFilepath << " to memory\n\n\n";
        return 1;
    }

    //latch tail to head
    size_t logTail (m_pLogDebug->logHead);

    while (true)
    {
        //if head moved forward
        while (logTail != m_pLogDebug->logHead)
        {
            auto& logDebugEntry = m_pLogDebug->log[logTail];

            printDebugLogEntry (logDebugEntry);

            //try to catch up with head
            logTail = (logTail + 1) & (kMaxDebugEntries - 1);

            //wait for 10 milliseconds...if there's no activity. (not too sure what that means)
            juce::Time::waitForMillisecondCounter (juce::Time::getMillisecondCounter() + 10);
        }
    }

    return 0;
}