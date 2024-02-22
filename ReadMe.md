# Week 3 Lab: Verification

**Exercise 2:** Since main goal was to test the model's evolution for multiple initial values, I chose to test a few initial values for numerous cycles: I first had to test if asserting `reset` properly initialized the model. I then used a for-loop to continue testing the model for some large numbers of cycles (I chose 10000).


**Exercise 4:** To test a Don't Care for signal, we must test that our model's output never changes for all possible inputs for said signal.