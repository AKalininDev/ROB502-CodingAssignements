# FA24_ROB502

## Setup
Fork
- Click fork on the top right
- Select namespace, choose your username
- Select Visibility to Private
- Click Fork Project

Clone repo to local machine
- Copy the clone with HTTPS link
- Open a terminal in Ubuntu
- Using the terminal navigate to a folder where you want to save homeworks
- Install Git, Clone repo, set upstream

```
sudo apt update
sudo apt install git
git clone <paste HTTPS link>
cd your_repo_name
git remote add upstream https://gitlab.eecs.umich.edu/thiruchl/fa23_rob502.git
```

## How to fetch new homeworks
- Fetch from upstream

```
git fetch upstream main
```

## How to pull new homeworks
- Pull from upstream

```
git pull upstream main
```