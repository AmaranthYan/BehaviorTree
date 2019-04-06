#pragma once

namespace BTree
{
	class Node
	{
	public:
		enum EState
		{
			Idle,
			Running,
			Success,
			Failure
		};

		Node() : state(EState::Idle) {}
		virtual ~Node() = default;

		EState Tick();

	protected:
		virtual void Enter() {}
		virtual void Exit() {}

		virtual EState Run() = 0;

	private:
		EState state;
	};
}