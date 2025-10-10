#include <Steel/Appout/CConv.hpp>

using namespace Appout;


void ThisCall_Push()
{
	__asm
	{
		push ecx
	};
}

void ThisCall_Pop()
{
	__asm
	{
		pop ecx
	};
}

ICConv::PushCallback CConv::ThisCall::Push()
{
	return ThisCall_Push;
}

ICConv::PushCallback CConv::ThisCall::Pop()
{
	return ThisCall_Pop;
}