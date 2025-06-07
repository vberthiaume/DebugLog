#include "DebugLog.hpp"

//==============================================================================
int main (int /*argc*/, char** /*argv[]*/)
{
    std::cout << "ProPhat Debug Log Reader" << std::endl;

    //Map file to memory..
    juce::MemoryMappedFile logDebugMapping (memoryMappedFile, juce::MemoryMappedFile::readOnly, false);
    DebugLog*              m_pLogDebug = (DebugLog*) logDebugMapping.getData();
    if (! m_pLogDebug)
    {
        std::cerr << "\n\nError! Failed to map file " << memoryMappedFile.getFullPathName() << " to memory\n\n\n";
        jassertfalse;
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
