#include "robots.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

struct Job
{
  int id;
  std::string name;
};

using namespace std;

// define and implement a function here called compareBotsByName
// it should be of the proper form to be used as the comparison
// function in std::sort. You will use compareBotsByName and std::sort
// to sort a std::vector<Robot>
bool compareBotsByName(const Robot &bot1, const Robot &bot2)
{
  return bot1.getName() < bot2.getName();
}

void loadBots(std::istream &botStream, std::queue<Robot> &bot_queue)
{
  string bot_info;
  while (getline(botStream, bot_info))
  {
    istringstream botStream(bot_info);
    string name, type;
    botStream >> name >> type;
    Robot bot(name, type);
    bot_queue.push(bot);
  }
}

void loadJobs(std::istream &jobStream, std::queue<Job> &job_queue)
{
  string job_info;
  while (getline(jobStream, job_info))
  {
    istringstream jobStream(job_info);
    int job_id;
    string job;
    jobStream >> job_id >> job;
    Job job_obj;
    job_obj.id = job_id;
    job_obj.name = job;
    job_queue.push(job_obj);
  }
}

void assignJobs(queue<Job> &jobs, std::queue<Robot> &bot_queue)
{
  while (!jobs.empty())
  {
    Job job = jobs.front();
    jobs.pop();

    for (int i = 0; i < bot_queue.size(); i++)
    {
      Robot bot = bot_queue.front();
      bot_queue.pop();

      string type = bot.getType();
      vector<string> qualifiedJobs = TYPES2JOBS.at(type);

      if (find(qualifiedJobs.begin(), qualifiedJobs.end(), job.name) != qualifiedJobs.end())
      {
        bot.assignJob(job.id);
        bot_queue.push(bot);
        break;
      }
      else
      {
        bot_queue.push(bot);
      }
    }
  }
}

int main()
{
  ifstream botfile("bots.txt");
  ifstream jobfile("jobs.txt");
  ofstream outfile("output.txt");

  queue<Robot> bot_queue;
  queue<Job> job_queue;

  // read the robots from botfile in to bot_queue
  // make sure you've looked at the definition
  // of the Robot class in robots.h first
  loadBots(botfile, bot_queue);
  loadJobs(jobfile, job_queue);

  // read in each job id and job in jobfile
  // and assign them to the robots as described in the problem

  assignJobs(job_queue, bot_queue);

  // now that the jobs are assigned, get the robots from the queue
  // and put them in the bots vector
  // then sort that vector alphabetically using std::sort
  // you will need to use the compareBotsByName function above
  vector<Robot> bots;
  while (!bot_queue.empty())
  {
    bots.emplace_back(bot_queue.front());
    bot_queue.pop();
  }

  sort(bots.begin(), bots.end(), compareBotsByName);

  for (int i = 0; i < bots.size(); i++)
  {
    cout << bots[i].print(false);
    outfile << bots[i].print(false);
  }

  return 0;
}
