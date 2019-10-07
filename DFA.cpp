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
	DFA<char> dfa1(0, false);
	// Checks if DFA is my name
	// Test 'James'
	//State : 1  false
	//State : 2  false
	//State : 3  false
	//State : 4  false
	//State : 5  true
	dfa1.add_state(1, false);
	dfa1.add_state(2, false);
	dfa1.add_state(3, false);
	dfa1.add_state(4, false);
	dfa1.add_state(5, true);
	dfa1.add_transition(0, 'j', 1);
	dfa1.add_transition(1, 'a', 2);
	dfa1.add_transition(2, 'm', 3);
	dfa1.add_transition(3, 'e', 4);
	dfa1.add_transition(4, 's', 5);
	// Checks for even length string from alphabet 01
	// Test 1010
	//State : 1  false
	//State : 0  true
	//State : 1  false
	//State : 0  true
	DFA<char> dfa2(0, true);
	dfa2.add_state(1, false);
	dfa2.add_transition(0, '0', 1);
	dfa2.add_transition(0, '1', 1);
	dfa2.add_transition(1, '0', 0);
	dfa2.add_transition(1, '1', 0);
	// Checks for strings that contain only 1's from alphabet 01
	/*
	Test 1111
	State : 1  true
	State : 1  true
	State : 1  true
	State : 1  true
	*/
	DFA<char> dfa3(0, false);
	dfa3.add_state(1, true);
	dfa3.add_transition(0, '1', 1);
	dfa3.add_transition(1, '1', 1);
	// Checks if the string is a binary number
	/*
	Test 101
	State: 1  true
	State: 1  true
	State: 1  true
	*/
	DFA<char> dfa4(0, false);
	dfa4.add_state(1, true);
	dfa4.add_transition(0, '0', 1);
	dfa4.add_transition(0, '1', 1);
	dfa4.add_transition(1, '0', 1);
	dfa4.add_transition(1, '1', 1);
	// Checks if the DFA is an even number
	/*
	Test 1010
	State: 0  false
	State: 1  true
	State: 0  false
	State: 1  true
	*/
	DFA<char> dfa5(0, false);
	dfa5.add_state(1, true);
	dfa5.add_transition(0, '0', 1);
	dfa5.add_transition(0, '1', 0);
	dfa5.add_transition(1, '1', 0);
	dfa5.add_transition(1, '0', 1);
	// Checks if the DFA is an odd number
	/*
	Test 101
	State: 1  true
	State: 0  false
	State: 1  true
	*/
	DFA<char> dfa6(0, false);
	dfa6.add_state(1, true);
	dfa6.add_transition(0, '1', 1);
	dfa6.add_transition(0, '0', 0);
	dfa6.add_transition(1, '0', 0);
	dfa6.add_transition(1, '1', 1);
	// Checks for strings that contain only 0's from alphabet 01
	/*
	Test 001
	State: 1  true
	State: 1  true
	State: -1  false
	*/
	DFA<char> dfa7(0, false);
	dfa7.add_state(1, true);
	dfa7.add_transition(0, '0', 1);
	dfa7.add_transition(1, '0', 1);
	// Checks if a word contains the word cat inside of it
	/*
	Test car
	State: 1  false
	State: 2  false
	State: -1  false
	*/
	DFA<char> dfa8(0, false);
	dfa8.add_state(1, false);
	dfa8.add_state(2, false);
	dfa8.add_state(3, true);
	dfa8.add_transition(0, 'c', 1);
	dfa8.add_transition(1, 'a', 2);
	dfa8.add_transition(2, 't', 3);
	dfa8.add_transition(-1, 'c', 1);
	// Checks if a word does not contain the word cat inside of it
	/*
	Test cat
	State: 1  true
	State: 2  true
	State: 3  false
	*/
	DFA<char> dfa9(0, true);
	dfa9.add_state(1, true);
	dfa9.add_state(2, true);
	dfa9.add_state(3, false);
	dfa9.add_transition(0, 'c', 1);
	dfa9.add_transition(1, 'a', 2);
	dfa9.add_transition(2, 't', 3);
	dfa9.add_transition(-1, 'c', 1);
	// Checks if the string is in the formet of /*/ with any number of *
	/*
	Test ///
	State: 1  false
	State: 3  true
	State: -1  false
	*/
	DFA<char> dfa10(0, false);
	dfa10.add_state(1, false);
	dfa10.add_state(2, false);
	dfa10.add_state(3, true);
	dfa10.add_transition(0, '/', 1);
	dfa10.add_transition(1, '/', 3);
	dfa10.add_transition(1, '*', 2);
	dfa10.add_transition(2, '*', 2);
	dfa10.add_transition(2, '/', 3);
	// Checks if the string is in the formet of /*/ with at least one *
	/*
	Test //
	State: 1  false
	State: -1  false
	*/
	DFA<char> dfa11(0, false);
	dfa11.add_state(1, false);
	dfa11.add_state(2, false);
	dfa11.add_state(3, true);
	dfa11.add_transition(0, '/', 1);
	dfa11.add_transition(1, '*', 2);
	dfa11.add_transition(2, '*', 2);
	dfa11.add_transition(2, '/', 3);
	// Checks to see if the number in the string is bigger than 0 in binary
	/*
	Test 000
	State: 0  false
	State: 0  false
	State: 0  false
	*/
	DFA<char> dfa12(0, false);
	dfa12.add_state(1, true);
	dfa12.add_transition(0, '0', 0);
	dfa12.add_transition(0, '1', 1);
	dfa12.add_transition(1, '0', 1);
	dfa12.add_transition(1, '1', 1);
	while (true)
	{
		cout << "State: " << dfa12.state() << "  " << (dfa12.is_accepting() ? "true" : "false") << endl;
		if (cin.peek() == '\n')
			break;
		cin >> noskipws >> input;
		dfa12.input(input);
	}
  	return 0;
}
