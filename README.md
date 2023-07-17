# QJump over NIC queue

In this project we are going to use Rustlang in order to reschedule linux
network interface card processes queue. We are going to send the less important
processes like background processes, docker containers, etc to the back of the queue
so that our user process will get in front.
