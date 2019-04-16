#pragma once

#include "Composite.h"

namespace BTree
{
	class Parallel : public Composite
	{
	public:
		Parallel() : stop_on_fail(false) {}
		Parallel(bool stop_on_fail) : stop_on_fail(stop_on_fail) {}

		void SetStopOnFail(bool stop_on_fail);

	protected:
		EState Run() override;

	private:
		bool stop_on_fail;
	};
}