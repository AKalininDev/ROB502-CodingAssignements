import lcm
import time
import numpy as np
from block_goal_msg import block_goal_t


def read_goal(fname: str) -> np.ndarray:

    with open(fname, "r") as f:
        lines = [line.strip() for line in f if line.strip()]

    translation = np.fromstring(lines[0], sep=" ")
    rotation = np.array([np.fromstring(line, sep=" ") for line in lines[1:4]])

    transform = np.eye(4)
    transform[:3, 3] = translation
    transform[:3, :3] = rotation

    return transform


def publish_transform(transform: np.ndarray) -> None:

    lc = lcm.LCM()

    # build message
    msg = block_goal_t()
    msg.transform = transform.tolist()
    msg.timestamp = int(time.time())

    lc.publish("BLOCK_GOAL", msg.encode())

    return None


if __name__ == "__main__":

    transform = read_goal("inputs1.txt")

    while True:
        publish_transform(transform)
        time.sleep(0.1)
