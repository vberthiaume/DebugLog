#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#if JUCE_WINDOWS
//TODO
jassertfalse;
static const juce::File memoryMappedFile { "/tmp/ProPhatSharedMemory" };
#else
static const juce::File memoryMappedFile { "/tmp/ProPhatSharedMemory" };
#endif

//static const auto memoryMappedFile { juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory).getChildFile("ProPhatSharedMemory") };

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
