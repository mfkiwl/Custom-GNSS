#ifndef TRACK_L1CA_H
#define TRACK_L1CA_H

#include <stdint.h>
#include "tools.h"
#include "filters.h"

class GPSL1CATracker
{
public:
    GPSL1CATracker(
        int sv,
        double fs = 69.984e6,
        double fc = 9.334875e6,
        double doppler = 0,
        double code_phase = 0);

    ~GPSL1CATracker();

    void track(uint8_t *signal, long long size);

private:
    int sv;
    double fs;
    double fc;
    double doppler;
    double code_off;

    // NCOs
    double code_phase;
    double code_rate;
    double carrier_phase;
    double carrier_rate;

    // Code generator
    int start_chip;
    CACodeGenerator *ca_code_early;

    // Code generator outputs
    uint8_t code_early;
    uint8_t code_prompt;
    uint8_t code_late;

    // Accumulators (early, prompt, late for I and Q)
    int ie;
    int qe;
    int ip;
    int qp;
    int il;
    int ql;

    // Variable to detect if this epoch has been processed
    bool epoch_processed;

    // DLL filter
    SecondOrderPLL *dll;

    // PLL filter
    SecondOrderPLL *pll;

    long long ms_elapsed;

    // Prompt buffers
    double ip_buffer[100];
    double qp_buffer[100];
    int prompt_len;
    int prompt_idx;

    // Private functions
    void update_sample(uint8_t signal_sample);
    void update_epoch();
};

#endif // TRACK_L1CA_H