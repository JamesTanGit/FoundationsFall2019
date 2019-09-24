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

template<typename T>
DFA<T>::DFA(int initial, bool isfinal)
{
	m_initial = initial;
	m_state = initial;
	add_state(initial, isfinal);
	add_state(-1, false);	// State not known
}

template<typename T>
void DFA<T>::add_state(int state, bool isfinal)
{
	m_states.insert(state);
	if (isfinal)
	{
		m_final_states.insert(state);
	}
}

template<typename T>
void DFA<T>::add_transition(int src, T input, int dest)
{
	m_transitions.insert(pair<pair<int, T>, int> (pair<int, T>(src, input), dest));
}

template<typename T>
int DFA<T>::input(T input)
{
	auto tr = make_pair(m_state, input);
	//Without this if statement, it accepts no strings
	//With this if statement, it accepts only the empty string
	if (input == ' ')
		return m_initial;
	if (m_transitions.count(tr) > 0)
	{
		auto it = m_transitions.find(tr);
		return m_state = it->second;
	}
	else
	{
		return m_state = -1;
	}
}

template<typename T>
bool DFA<T>::is_accepting()
{
	return m_final_states.count(m_state) != 0;
}

template<typename T>
int DFA<T>::state()
{
	return m_state;
}

int main(int argc, char* argv[])
{
	char input;
	char input2;
	cout << "Give me a character so I can return a DFA that accepts only strings of exactly that character: ";
	cin >> input2;
	cin.ignore(256, '\n');
	DFA<char> dfa(0, false);
	dfa.add_state(1, true);
	dfa.add_transition(0, input2, 1);
	dfa.add_transition(1, input2, 1);
	while (true)
	{
		cout << "State: " << dfa.state() << "  " << (dfa.is_accepting() ? "true" : "false") << endl;
		if (cin.peek() == '\n')
			break;
		cin >> noskipws >> input;
		dfa.input(input);
	}
  return 0;
}
