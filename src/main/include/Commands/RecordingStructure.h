#pragma once

struct RecordingStructure
{
    static const int SYNC1 = 0x0CAFE;
    static const int SYNC2 = 0x0BEEF;

    RecordingStructure() 
    {
        m_sync1 = SYNC1; 
        m_sync2 = SYNC2;
    }

    int m_sync1;
    float m_left;
    float m_right;
    int m_sync2;
};
