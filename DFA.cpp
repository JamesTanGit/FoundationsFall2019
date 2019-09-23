#include <iostream>
#include <set>
#include <map>
using namespace std;

template<typename T>
class DFA
{
public:
	DFA(int initial, bool isfinal);
	void add_state(int state, bool isfinal);
	void add_transition(int src, T input, int dest);
	int input(T input);
	bool is_accepting();
	int state();

private:
	int m_initial;
	int m_state;
	set<int> m_states;
	set<int> m_final_states;
	map<pair<int, T>, int> m_transitions;
};

int main(int argc, char* argv[])
{
  return 0;
}
