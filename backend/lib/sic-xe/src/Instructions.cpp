#include "Instructions.hpp"
#include "DecodedInstruction.hpp"
#include "architecture/CPUState.hpp"
#include "memory/MemoryAccessor.hpp"

#define DEFINE_INSTRUCTION(name) \
bool name::execute(ExecutionContext& context) const \
{ \
    throw UnimplementedInstruction(#name);\
}

bool AddInstruction::execute(ExecutionContext& context) const 
{ 
    context.registers.write("A", context.registers.read("A") + context.instruction.immediate);

    return true;
}   

bool StchInstruction::execute(ExecutionContext& context) const 
{ 
    std::vector<byte_t> buf = {static_cast<byte_t>(context.registers.read("A") & 0xff)};
    context.memory.write( context.instruction.displacement , buf);

    return true;
}   

bool StsInstruction::execute(ExecutionContext& context) const 
{ 
    uint64_t s = context.registers.read("S");

    std::vector<byte_t> buf = {
        static_cast<byte_t>(s & 0xff),
        static_cast<byte_t>(s & (0xff << 8)),
        static_cast<byte_t>(s & (0xff << 16))
    };

    context.memory.write( context.instruction.displacement, buf);

    return true;
}   

// DEFINE_INSTRUCTION(StsInstruction)



bool SttInstruction::execute(ExecutionContext& context) const 
{ 
    uint64_t t = context.registers.read("T");

    std::vector<byte_t> buf = {
        static_cast<byte_t>((t >> 16) & 0xff), // MSB
        static_cast<byte_t>((t >> 8) & 0xff),
        static_cast<byte_t>(t & 0xff)          // LSB
    };

    context.memory.write(context.instruction.displacement, buf);

    return true;
} 

// DEFINE_INSTRUCTION(SttInstruction)



bool JltInstruction::execute(ExecutionContext& context) const 
{ 
    uint64_t cc = context.registers.read("SW") & 0x030000; // máscara do CC (bits 16-17, conforme decisão do Beck/PR)

    if (cc == 0x010000) { // 01 = <
        context.registers.write("PC", context.instruction.displacement);
        return false; // false porque o PC já foi setado manualmente, não deve ser incrementado de novo em step()
    }

    return true;
}






//DEFINE_INSTRUCTION(JltInstruction)






DEFINE_INSTRUCTION(AddFInstruction)
DEFINE_INSTRUCTION(AddRInstruction)
DEFINE_INSTRUCTION(AndInstruction)
DEFINE_INSTRUCTION(ClearInstruction)
DEFINE_INSTRUCTION(CompInstruction)
DEFINE_INSTRUCTION(CompFInstruction)
DEFINE_INSTRUCTION(CompRInstruction)
DEFINE_INSTRUCTION(DivInstruction)
DEFINE_INSTRUCTION(DivFInstruction)
DEFINE_INSTRUCTION(DivRInstruction)
DEFINE_INSTRUCTION(FixInstruction)
DEFINE_INSTRUCTION(FloatInstruction)
DEFINE_INSTRUCTION(HioInstruction)
DEFINE_INSTRUCTION(JInstruction)
DEFINE_INSTRUCTION(JeqInstruction)
DEFINE_INSTRUCTION(JgtInstruction)
DEFINE_INSTRUCTION(JsubInstruction)
DEFINE_INSTRUCTION(LdaInstruction)
DEFINE_INSTRUCTION(LdbInstruction)
DEFINE_INSTRUCTION(LdchInstruction)
DEFINE_INSTRUCTION(LdfInstruction)
DEFINE_INSTRUCTION(LdlInstruction)
DEFINE_INSTRUCTION(LdsInstruction)
DEFINE_INSTRUCTION(LdtInstruction)
DEFINE_INSTRUCTION(LdxInstruction)
DEFINE_INSTRUCTION(LpsInstruction)
DEFINE_INSTRUCTION(MulFInstruction)
DEFINE_INSTRUCTION(MulRInstruction)
DEFINE_INSTRUCTION(NormInstruction)
DEFINE_INSTRUCTION(OrInstruction)
DEFINE_INSTRUCTION(RdInstruction)
DEFINE_INSTRUCTION(RmoInstruction)
DEFINE_INSTRUCTION(RsubInstruction)
DEFINE_INSTRUCTION(ShiftLInstruction)
DEFINE_INSTRUCTION(ShiftRInstruction)
DEFINE_INSTRUCTION(SioInstruction)
DEFINE_INSTRUCTION(SskInstruction)
DEFINE_INSTRUCTION(StaInstruction)
DEFINE_INSTRUCTION(StbInstruction)

DEFINE_INSTRUCTION(StfInstruction)
DEFINE_INSTRUCTION(StiInstruction)
DEFINE_INSTRUCTION(StlInstruction)
DEFINE_INSTRUCTION(StswInstruction)
DEFINE_INSTRUCTION(StxInstruction)
DEFINE_INSTRUCTION(SubInstruction)
DEFINE_INSTRUCTION(SubFInstruction)
DEFINE_INSTRUCTION(SubRInstruction)
DEFINE_INSTRUCTION(SvcInstruction)
DEFINE_INSTRUCTION(TdInstruction)
DEFINE_INSTRUCTION(TioInstruction)
DEFINE_INSTRUCTION(TixInstruction)
DEFINE_INSTRUCTION(TixRInstruction)
DEFINE_INSTRUCTION(WdInstruction)

#undef DEFINE_INSTRUCTION