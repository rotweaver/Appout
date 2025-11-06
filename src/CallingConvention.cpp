#include <Appout/CallingConvention.hpp>
#include <Appout/Assembler/x86Assembler.hpp>

#include <Appout/Instance.hpp>


__declspec(naked) void thisCallWrapper()
{
	__asm
	{
		push EBP
		mov EBP, ESP

		push EAX

		mov EAX, [EBP - 4]; get argument count
		mov EDX, [EBP - 8]; get argument size

		sub EBP, EAX ; Move to start of args

		loop_begin:
		sub EBP, 4
		push [EBP]
		loop loop_begin

		push ECX

		ret
	}
}

__declspec(naked) void stdcallWrapper()
{
	__asm
	{
		push EBP
		mov EBP, ESP

		push EAX

		mov EAX, [EBP - 0x4]; get argument size

		sub EBP, EAX; Move to start of args

		loop_begin :
		sub EBP, 4
		push[EBP]
		loop loop_begin

		ret
	}
}

__declspec(naked) void stdcallUnwrapper() // turn cdecl into stdcall
{
	__asm
	{

	}
}

using namespace Appout;

CallingConvention::CallingConvention(const type& value) : Value(value)
{

}
CallingConvention::CallingConvention(const CallingConvention& source) : Value(source.Value)
{

}

CallingConvention::operator int()
{
	return Value;
}
CallingConvention& CallingConvention::operator=(type t)
{
	Value = t;
	return *this;
}
bool CallingConvention::operator==(int other) const
{
	return Value == other;
}
bool CallingConvention::operator==(const CallingConvention& other) const
{
	return Value == other.Value;
}
const char* CallingConvention::ToString() const
{
	switch (Value)
	{
	case CDecl:
		return "__cdecl";
	case ThisCall:
		return "__thiscall";
	case FastCall:
		return "__fastcall";
	case STDCall:
		return "__stdcall";
	default:
		return "Unknown Convention";
	}
}






void fromCdecl(MemoryPoolBase& memoryPool, const std::vector<PrimitiveType>& params)
{
	x86Assembler ass = x86Assembler(memoryPool);

}


void CallingConvention::CreateWrapper(CallingConvention cconv, const std::vector<PrimitiveType>& params, MemoryPoolBase& memoryPool)
{
	switch (cconv)
	{
	case CDecl:
		break;
	case FastCall:
		break;
	case STDCall:
		stdcallWrapper();
		break;
	default:
		break;
	}
}

void CallingConvention::AssembleWrapper(CallingConvention cconv, MemoryPoolBase& memoryPool)
{
	switch (cconv)
	{
	case FastCall:
		break;
	case STDCall:
		break;
	default:
		break;
	}
}
void CallingConvention::AssembleUnwrapper(type cconv, uint32_t paramCount)
{

}



void CallingConvention::assembleThisCallWrapper(uint32_t paramCount)
{
	x86Assembler assembler = x86Assembler(Instance::Get()->MemoryPool());

	// assembler.push_r32(x86Assembler::Register::EBP); // preserve OG stack frame
	// assembler.push_r32(x86Assembler::Register::ECX); // preserve OG "this"

	// assembler.push_r32(x86Assembler::Register::EAX); // Preserve OG EAX
	assembler.pop_r32(x86Assembler::Register::EDX);

	// Setup prologue
	assembler.push_r32(x86Assembler::Register::EBP);
	assembler.mov_EBP_ESP();


	// Loop to push OG stack vars
	// sub ebp, 0x4
	assembler.push_r32(x86Assembler::Register::EBP);
	assembler.loop(-6);

	assembler.push_r32(x86Assembler::Register::ECX);
}
void CallingConvention::assembleThisCallUnwrapper(int32_t paramCount)
{
	x86Assembler assembler = x86Assembler(Instance::Get()->MemoryPool());



	assembler.pop_r32(x86Assembler::Register::ECX); // Retrieve original "this"
	assembler.pop_r32(x86Assembler::Register::EBP); // Restore OG stack
}

