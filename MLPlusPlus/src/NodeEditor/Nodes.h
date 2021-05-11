#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>

namespace Nodes
{
	class Node 
	{
	public:
		int start_id;
		Node(int id) : start_id(id) {}
		virtual void show() = 0;
		virtual int lastIdOffset() const = 0;
	};

	class Main: public Node
	{
	public:
		Main(int id);
		void show() override;
		int lastIdOffset() const override;
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class LinearRegression : public Node
	{
	public:
		LinearRegression(int id);
		void show() override;
		int lastIdOffset() const override;
		static inline constexpr int getIdIncreament() { return 4; }
	};

	class LR_SetLearningRate : public Node
	{
	public:
		LR_SetLearningRate(int id);
		void show() override;
		int lastIdOffset() const override;
		static inline constexpr int getIdIncreament() { return 5; }
	};
}