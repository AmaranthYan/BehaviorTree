#pragma once

#include "Decorator.h"

namespace BTree
{
	class Loop : public Decorator
	{
	public:
		Loop(int times = 0) : times(times) {}

	protected:
		void Enter() override;
		EState Run() override;

	private:
		int times;
		int count;
	};
}