# Jogo Par
Jogo Par is a 4 players game.
It requires 5 computers, one of them will be the referee and can be mounted on a kobuki turtlebot, while the others will be distributed by four players, who should sit in a circle around the robot.
 In each round of the game, all players can decide to chose one of 5 cards (possible moves). If one player chooses a card, for every other player that chooses the same, the first will receive 2 points, hence, the goal of the game is to score greatest amount of pairs.
Each game has a minimum of five rounds, but, if  by the end of it a winner has not been decided, the game continues until one is found.
Then the referee announces, who is victorious, then turns towards him and takes a picture

As mentioned before, everyone sits with their own computer where they choose
their card by sending the name of it to the “referee”.  The referee then “collects”
all the cards and computes the scoreboard with current points for the given
round.


				I hope that you enjoy it :D


(The image taking is commented out, and the velocity topic was replaced by its representative on turtlesim,
because the game can be player with the turtlesim)

# Setup
- The players must be sited in the corners of a 3m square, while the robot stands in the center 
- Every player sits around in order from player 1 to 4 anticlockwise. 
- The robot starts facing player 1
- The first node to be called should be the referee, and only then the players
- After the game is over, all the players should type "quit"
