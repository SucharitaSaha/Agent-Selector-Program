/*
PROBLEM STATEMENT:


You are given the following data for agents
    * is_available
    * available_since (the time since the agent is idle)
    * roles (a list of roles the user has, e.g. spanish speaker, sales, support etc.)

When an issue comes in we need to present the issue to 1 or many agents based on an agent selection mode. 
An agent selection mode can be all available, max idle or random.

    * In "all available" mode the issue is presented to all agents so they pick the issue if they want.
    * In "least busy" the issue is presented to the agent that has been idle for the longest.
    * In "random mode" we randomly pick an agent. 

An issue also has one or many roles (sales/support e.g.).Issues are presented to agents only with matching roles.

Implement a function that takes an input the list of agents with their data, agent selection mode and 
returns a list of agents the issue should be presented to.

*/

#include <bits/stdc++.h>
using namespace std;

class Agent {
	public:
		vector<string> roles; // roles the agent is specialised on
		int id;
		bool is_available; // availability status of agent
		float available_since; // idle time

		Agent(vector<string> _roles, int _id, bool _is_available, float _available_since) {
			id = _id;
			roles = _roles;
			is_available = _is_available;
			available_since = _available_since;
		}

		// called when creating an empty array of agents
		Agent() {

		}
};


/*
	function to return a vector of the IDs of those agents which have all the roles (provided in the roles[] array)
	as specialization and as per the mode of issue query.
*/
vector<int> findMatchingAgents(string roles[], int no_roles, Agent agents[], int no_agents, int mode) {

	// will contain the agents which have specialization of all the roles provided
	vector<Agent> matchingAgents; 

	// will contain the IDs of those agents present in the matchingAgents vector and filtered as per the mode provided
	vector<int> matchingAgentsId;

	/*
		iterate through the agents array and find out those agents which have all the specialization
		provided in the roles array
	*/
	for(int j=0; j<no_agents; j++) {

		// if current agent is not available, check for the next agent
		if(!agents[j].is_available) {
			continue;
		}

		bool role_present = true;

		/*
			iterate over the roles to check whether it exists as specialization
			of the current agent. 
		*/
		for(int i=0; i<no_roles; i++){

			// get the specialized roles for the current agent
			vector<string> agent_roles = agents[j].roles;

			// if the current role is not present in agent's roles, then break from the inner role check loop
			if(find(agent_roles.begin(), agent_roles.end(), roles[i]) == agent_roles.end()) {
				role_present = false;
				break;
			}
		}

		// if all roles are present in the current agent's specialized roles, then add it
		if(role_present) {
			matchingAgents.push_back(agents[j]);
		}
	}


	
	// if no agent available or mode = 1 i.e, return all matching agents
	if(matchingAgents.size() == 0 || mode == 1){
		for(int i=0; i<matchingAgents.size(); i++){
			matchingAgentsId.push_back(matchingAgents[i].id);
		}
	}

	// find out that agent who is idle for the longest time i.e having max available_since time.
	else if(mode == 2) {
		float max_available_since = matchingAgents[0].available_since;
		int id = matchingAgents[0].id;

		for(int i=1; i<matchingAgents.size(); i++){
			if(matchingAgents[i].available_since > max_available_since) {
				max_available_since = matchingAgents[i].available_since;
				id = matchingAgents[i].id;
			}
		}
		matchingAgentsId.push_back(id);
	}

	// return a random agent out of the matching agents
	else {
		// random_idx varies from 0 to size of matchingAgents
		int random_idx = rand() % matchingAgents.size();
		matchingAgentsId.push_back(matchingAgents[random_idx].id);
	}
	
	return matchingAgentsId;
}


int main() {
	int no_agents;
	cout << "\nEnter the number of agents: ";
	cin >> no_agents;

	Agent agents[no_agents];

	cout << "\nEnter the agent info as asked below \n";

	/*
		input for agent details
	*/
	for(int i=0; i<no_agents; i++) {
		vector<string> roles;
		int id;
		bool status;
		float available_since;

		cout << "\nDetails for agent " << i+1;

		cout << "\nEnter ID: ";
		cin >> id;

		cout << "Enter status(1 for available / 0 for unavailable): ";
		cin >> status;

		cout << "Enter no of roles: ";
		int no_roles;
		cin >> no_roles;
		while(no_roles--) {
			cout << "Enter name of role: ";
			string role;
			cin >> role;
			roles.push_back(role);
		}

		cout << "Enter available_since time difference(float): ";
		cin >> available_since;

		agents[i] = Agent(roles, id, status, available_since);
	}

	cout << "\nEnter the number of issues: ";
	int no_issues;
	cin >> no_issues;

	/*
		input for issue details
	*/
	for(int i=0; i<no_issues; i++) {
		cout << "\nDetails of issue no." << i+1;

		int no_roles;
		cout << "\nEnter the number of roles: ";
		cin >> no_roles;

		string roles[no_roles];

		for(int i=0; i<no_roles; i++) {
			cout << "Enter role for the current issue: ";
			cin >> roles[i];
		}

		int query_mode;
		cout << "Enter the mode of issue distribution(1 for all available, 2 for max idle, 3 for random): ";
		cin >> query_mode;

		cout << "\nFollowing are the ID of the agents who are available for the queried issue: ";

		vector<int> reqAgentsId = findMatchingAgents(roles, no_roles, agents, no_agents, query_mode);

		// printing the IDs
		for(int i=0; i<reqAgentsId.size(); i++) {
			cout << reqAgentsId[i] << " ";
		}

		cout << "\n\n";
	}
}