#pragma once

#include <imgui.h>
#include <imfilebrowser.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Object.h>
#include <NodeEditor/NodeLink.h>
#include <Plotter/Plotter.h>
#include <rapidcsv.h>

struct Graphs
{
	inline static Plotter* plotter = nullptr;
};

namespace Nodes
{
	class Pin 
	{
	public:
		int id;
		DataType type;
		Object* obj;
		
		Pin(int id, DataType type) : id(id), type(type) {}
	};

	class Node 
	{
	public:
		int start_id;
		int p = -1, n = -1;
		Node* prev = nullptr;
		Node* next = nullptr;
		std::vector<Pin> inputs;
		std::vector<Pin> outputs;
		Object* output = nullptr;
		char error[128] = "";
		bool hasError = false;

		Node(int id) : start_id(id) {}
		Node(int id, int p, int n) : start_id(id), p(p), n(n) {}

		virtual void show() = 0;
		virtual void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) = 0;
		virtual void clean() = 0;
		virtual int lastIdOffset() const = 0;
	};

	class Main: public Node
	{
	public:
		Main(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 2; }
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class LinearRegression : public Node
	{
	private:
	public:
		LinearRegression(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 4; }
		static inline constexpr int getIdIncreament() { return 4; }
	};

	class LR_Train : public Node
	{
	private:
		static inline int s_count = 0;
		int count = 0;
		char rate[8] = "0.01";
		char iter[8] = "1000";
	public:
		LR_Train(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override; 
		void clean() override;
		
		inline int lastIdOffset() const override { return 9; }
		static inline constexpr int getIdIncreament() { return 9; }
	};

	class LR_Predict :public Node
	{
	private:
		std::vector<double> y;
	public:
		LR_Predict(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};

	class Set : public Node
	{
	private:
		static inline int s_count = 0;
		int count;
		char name[64] = "";
		Object* object;
		bool pinParsed = false;
	public:
		Set(int id, Object* obj = nullptr);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 5; }
		static inline constexpr int getIdIncreament() { return 5; }
	};
	
	class Get : public Node
	{
	private:
		Object* object;
	public:
		Get(int id, Object* obj);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 2; }
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class FileReader : public Node
	{
	private:
		static inline int s_count = 0;
		int count = 0;
		char filename[64] = "";
		char filepath[256] = "";
		bool fileSelection = false;
		ImGui::FileBrowser fileDialog;
		rapidcsv::Document doc;
	public:
		FileReader(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};

	class FR_ReadColumn :public Node
	{
	private:
		static inline int s_count = 0;
		int count = 0;
		std::vector<double> arr;
		char columnName[32] = "";
	public:
		FR_ReadColumn(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};

	class PlotGraph : public Node 
	{
	public:
		PlotGraph(int id);
		void show() override;
		void execute(std::vector<Node*>& nodes, std::vector<Link*>& links) override;
		void clean() override;

		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};
}