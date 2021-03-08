#include "Draw.hpp"
#include "Startup.hpp"
#include "NodeGeneration.hpp"
#include <iostream>
#include <cstdlib>
#include "forceDirectedPlacement.hpp"

int main(int argc, char* argv[])
{
	// Initialisation
	const auto windowWidth = 25<<5;
	const auto windowHeight = 75<<3;
	auto windowSize = Vector2(windowWidth, windowHeight);
	std::vector<Node*> nodes;

	// Handling parameters
	auto args = handleArgs(argc, argv);
	nodes = (args.fileName == nullptr) ?
		getNodesRandom(args.numNodes, args.seed) : handleFile(args.fileName);

	// Force directed placement
	const auto SPREADOFFSET = 1.0f; // Known as the C value
	auto spread = SPREADOFFSET * sqrtf(1.0f * windowWidth * windowHeight / args.numNodes);
	auto scale = windowWidth + windowHeight;
	auto fdp = FdpContext(nodes, windowSize, scale, spread, args.iterations);
	forceDirectedPlacement(fdp, args);
	Node::printNodesAndConnections(nodes);

	// Setting up window
	auto draw = new Draw((char*)"CPU Implementation", windowWidth, windowHeight);
	draw->draw(nodes);

	// Cleanup
	delete draw;
	nodes.clear();
	return 0;
}