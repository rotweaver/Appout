#pragma once

#include <cstdint>

#define NAKED __declspec(naked)

namespace Appout
{
	class ICConv
	{
	public:
		using PushCallback = void(*)();
		using PopCallback = void(*)();

		virtual PushCallback Push() = 0;
		virtual PopCallback Pop() = 0;
	};


	namespace CConv
	{
		class ThisCall : public ICConv
		{
		public:
			PushCallback Push();
			PopCallback Pop();
		};
	}

	namespace Wrapper
	{
		class ThisCall
		{
		public:
			void Wrap();
		};
	}
}