#include <mbed.h>
#include <rtos.h>

#include <vector>
#include <algorithm>

#include <helper-funcs.hpp>

#include "robot-devices.hpp"

#define MCP23017_I2C_READ (0x01)

bool testPass = false;
std::vector<unsigned int> freq1;
std::vector<unsigned int> freq2;

void run_test(I2C& i2c) {
    char buf[2];

    // For both frequencies, we check 1 additional address that should always
    // fail for the
    // case where there's a response on every valid address of the IO expander.
    for (unsigned int addrOffset = 0; addrOffset < 0x09; addrOffset++) {
        bool nack, ack = false;
        char addr = (0x40 | addrOffset);

        // The MCP23017's sequence for reading a register
        // ACKS should be received both times, but we OR them
        // together for the test.
        ack = i2c.write(addr);
        nack = i2c.read(addr, buf, 2);

        if (ack && !nack) freq1.push_back(addr);
    }
}

int main() {
    // GPIO0_BASE
    DigitalOut good(LED1, 0);
    DigitalOut bad1(LED2, 0);
    DigitalOut bad2(LED3, 0);
    DigitalOut pwr(LED4, 1);
    Serial pc(RJ_SERIAL_RXTX);
    I2C i2c(RJ_I2C_BUS);

    pc.baud(57600);
    pc.printf("START========= STARTING TEST =========\r\n\r\n");

    pwr = 0;
    RtosTimer live_light(imAlive, osTimerPeriodic, (void*)&pwr);
    live_light.start(250);

    pc.printf("--  Testing IO Expander at 100kHz\r\n");
    // Test on low bus frequency
    i2c.frequency(100000);
    run_test(i2c);

    pc.printf("--  Testing IO Expander at 400kHz\r\n");
    // Test on high bus frequency
    i2c.frequency(400000);
    run_test(i2c);

    // Test results
    pc.printf("\r\n100kHz Test:\t%s\t(%u ACKS)\r\n",
              freq1.empty() ? "FAIL" : "PASS", freq1.size());
    pc.printf("400kHz Test:\t%s\t(%u ACKS)\r\n",
              freq2.empty() ? "FAIL" : "PASS", freq2.size());

    // Store the number of ACKs from the low frequency so we can just modify its
    // vector instead of making a new one
    size_t freq1_acks = freq1.size();

    // Merge the 2 vectors together & remove duplicate values
    freq1.insert(freq1.end(), freq2.begin(), freq2.end());
    sort(freq1.begin(), freq1.end());
    freq1.erase(std::unique(freq1.begin(), freq1.end()), freq1.end());

    // Final results of the test
    testPass = (freq2.size() == freq1_acks) && freq1.size() == 9;

    pc.printf("\r\n=================================\r\n");
    pc.printf("========== TEST %s ==========\r\n",
              testPass ? "PASSED" : "FAILED");
    pc.printf("=================================DONE");

    // Turn on the corresponding LED(s)
    good = testPass;
    bad1 = !testPass;
    bad2 = !testPass;
    live_light.stop();
    pwr = testPass;

    while (true) {
        // Never return
        wait(2.0);
    }
}
