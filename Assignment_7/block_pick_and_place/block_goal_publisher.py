import lcm
import time
import numpy as np
from block_goal_msg import block_goal_t

def read_goal(fname):
    transformation = None
    # --- Your code here



     # ---

    return transform

def publish_transform(transform):
    # --- Your code here



    # ---

if __name__ == "__main__":
 
    transform = read_goal('inputs1.txt')
    
    while True:
        publish_transform(transform)
        time.sleep(0.1)
