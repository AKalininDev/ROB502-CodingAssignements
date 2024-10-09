#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

using State = vector<int>;  // this defines the type State to be a vector of ints
using Action = vector<int>; // this defines the type Action to be a vector of ints
using Policy = map<State, Action>;

// this function should print out a state to the given stream
// the ostream could be something like cout, or cerr
// or it could be a filestream
void printState(const State &state, ostream &stream)
{
    {
        for (int j = 0; j < state.size(); j++)
        {
            stream << state[j] << " ";
        }
        stream << endl;
    }
}

State dynamics(const State &state, const Action &action)
{
    State next_state(state.size());
    for (int j = 0; j < state.size(); j++)
    {
        next_state[j] = state[j] + action[j];
    }
    return next_state;
}

void loadPolicy(std::istream &policyStream, Policy &policy)
{
    std::string policyLine;

    // Read the rest of the policy lines
    while (std::getline(policyStream, policyLine))
    {
        std::istringstream policyLineStream(policyLine);
        State state(2);
        Action action(2);

        policyLineStream >> state[0] >> state[1] >> action[0] >> action[1];

        policy[state] = action;
    }
}

int main()
{

    ifstream policyfile("policy.txt");
    ofstream outputfile("output.txt");

    const int StateSize = 2;
    const int ActionSize = 2;

    State key(StateSize);
    Action value(ActionSize);
    Policy policy;

    // read the policy file information into std::pair objects,
    // insert each std::pair into the map
    loadPolicy(policyfile, policy);

    // optional (but recommended) print out the policy to cout
    // to make sure that it was read in correctly
    for (auto &pair : policy)
    {
        printState(pair.first, cout);
        printState(pair.second, cout);
        cout << endl;
    }
    // read in rollout
    ifstream rolloutfile("rollout.txt");
    State startState(StateSize); // this stores the start stae
    int numSteps;                // this is the number of steps in the rollout
    rolloutfile >> startState.at(0);
    rolloutfile >> startState.at(1);
    rolloutfile >> numSteps;
    rolloutfile.close();

    // Now use the the policy map to do the rollout
    State currentState = startState;
    printState(currentState, outputfile);
    for (int i = 0; i < numSteps; i++)
    {
        if (policy.find(currentState) == policy.end())
        {
            cerr << "State " << currentState.at(0) << " " << currentState.at(1) << " is not in policy, terminating." << endl;
            outputfile.close();
            return 1;
        }
        Action action = policy[currentState];
        currentState = dynamics(currentState, action);
        printState(currentState, outputfile);
    }

    outputfile.close();
    return 0;
}
