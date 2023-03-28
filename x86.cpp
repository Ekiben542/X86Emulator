#include <iostream>
#include <cstdint>

class X86Emulator {
public:
    X86Emulator() {
        pc = 0;
        regs.fill(0);
    }

    void loadProgram(const uint8_t* program, size_t size) {
        std::memcpy(memory.data(), program, size);
    }

    void run() {
        while (true) {
            uint8_t opcode = memory[pc];
            pc++;

            switch (opcode) {
                case 0x90: // NOP
                    break;
                case 0xb8: // MOV EAX, imm32
                    regs[0] = *(uint32_t*)(memory.data() + pc);
                    pc += 4;
                    break;
                case 0xc3: // RET
                    return;
                default:
                    std::cerr << "Invalid opcode: " << opcode << std::endl;
                    return;
            }
        }
    }

private:
    uint32_t pc;
    std::array<uint32_t, 4> regs;
    std::array<uint8_t, 1024> memory;
};

int main() {
    uint8_t program[] = {0xb8, 0x01, 0x00, 0x00, 0x00, 0xc3}; // MOV EAX, 1; RET

    X86Emulator emulator;
    emulator.loadProgram(program, sizeof(program));
    emulator.run();

    std::cout << "Result: " << emulator.getRegister(0) << std::endl;

    return 0;
}
