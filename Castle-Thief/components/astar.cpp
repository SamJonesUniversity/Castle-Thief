#include "astar.h"
#include <LevelSystem.h>
#include <array>
#include <queue>

using namespace std;
using namespace sf;

//Node in search graph
class Node {
	private:
		Vector2i _pos;
		int _level;
		int _priority;
	public:
		Node() = default;
		Node(const Vector2i& pos, int level, int priority)
			: _pos(pos), _level(level), _priority(priority) {}

		const Vector2i& getPos() const { return _pos; }

		int getLevel() const { return _level; }

		int getPriority() const {return _priority; }

		unsigned int estimate(const Vector2i& dest) const {
			Vector2i delta = dest - _pos;
			return static_cast<unsigned int>(length(delta));
		}

		void updatePriority(const Vector2i& dest) {
		//Heuristic is just Euclidian distance.
		//Can be modified
		_priority = _level + estimate(dest) * 10;
		}

		void nextLevel() { _level += 10; }

		//used for priority ordering
		bool operator<(const Node& other) const {
			return _priority > other._priority;
		}
};

vector<Vector2i> pathFind(Vector2i start, Vector2i finish) {
	static std::array<sf::Vector2i, 4> directions = {
		Vector2i(1,0), Vector2i(0, 1), Vector2i(-1, 0), Vector2i(0, -1)};

		//This may not be the most effient mechanism but is not a problem if map isnt large.
		vector<vector<bool>> closed_nodes_map(ls::getWidth());
		vector<vector<int>> open_nodes_map(ls::getWidth());
		vector<vector<Vector2i>> direction_map(ls::getWidth());
		//Queue of nodes priority ordered
		priority_queue<Node> queue[2];
		//current pos in queue
		size_t queue_index = 0;

		//Initiialise lookup maps
		for (size_t y = 0; y < ls::getHeight(); y++) {
			for (size_t x = 0; x < ls::getWidth(); x++) {
				closed_nodes_map[x].push_back(0);
				open_nodes_map[x].push_back(0);
				direction_map[x].emplace_back(Vector2i(0, 0));
			}
		}

		//Add start node to queue
		Node n0(start, 0, 0);
		//Update priority of node
		n0.updatePriority(finish);
		//Push onto queue
		queue[queue_index].push(n0);
		//Update value in open_nodes_map
		open_nodes_map[start.x][start.y] = n0.getPriority();

		//Loop until queue is empty
		while (!queue[queue_index].empty()) {
			auto tmp = queue[queue_index].top();
			n0 = Node(tmp.getPos(), tmp.getLevel(), tmp.getPriority());
			auto pos = n0.getPos();

			//remove node from open list
			queue[queue_index].pop();
			open_nodes_map[pos.x][pos.y] = 0;
			//mark on closed list
			closed_nodes_map[pos.x][pos.y] = true;

			//check if reached goal
			if (pos == finish) {
				vector<Vector2i> path;
				while (!(pos == start)) {
					//get the direction
					auto dir = direction_map[pos.x][pos.y];
					// ad the current position to path
					path.push_back(pos);
					pos += dir;
				}
				//path is inverted
				reverse(begin(path), end(path));
				//return path
				return path;
			}

			//Not reached goal check 4 directions
			for (auto& dir : directions) {
				auto next = pos + dir;

				//check if next is valid
				if (!(next.x < 0 || next.x > ls::getWidth() || next.y < 0 || next.y > ls::getHeight() || 
				ls::getTile(Vector2ul(next.x, next.y)) == LevelSystem::WALL || closed_nodes_map[next.x][next.y])) {
					//Generate new node
					Node m0(next, n0.getLevel(), n0.getPriority());
					m0.nextLevel();
					m0.updatePriority(finish);

					//Check if new node has no prio
					if (open_nodes_map[next.x][next.y] == 0) {
						//update prop and add to queue
						open_nodes_map[next.x][next.y] = m0.getPriority();
						queue[queue_index].push(m0);
						//put the opposite direction in the map
						//backwards
						direction_map[next.x][next.y] = dir * -1;
					}
					//If it has a priority check if the priority is better on new route
					else if (open_nodes_map[next.x][next.y] > m0.getPriority()) {
						//Update prio information
						open_nodes_map[next.x][next.y] = m0.getPriority();
						//update direction map with inverse
						direction_map[next.x][next.y] = dir * -1;
						//now replace node via swapping across lists
						while (queue[queue_index].top().getPos() != next) {
							queue[1 - queue_index].push(queue[queue_index].top());
							queue[queue_index].pop();
						}
						queue[queue_index].pop();
						if (queue[queue_index].size() > queue[1 - queue_index].size()) {
							queue_index = 1 - queue_index;
						}
						while (!queue[queue_index].empty()) {
							queue[1 - queue_index].push(queue[queue_index].top());
							queue[queue_index].push(m0);
						}
							
					}
				}
			}
		}
		return vector<Vector2i>();
}