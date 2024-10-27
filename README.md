# Overview of the project:
This is a personal project to make a card game. The current version of the game is inspired by a game called The Fox in the Forest, which I really enjoyed playing. The objective of that game is to win tricks, but not to many. This game is built in C++ with the SFML library being used to handle the graphics.  The current version and some future plans are outlined below. I designed the Card sprites in Inkscape.

# The current game:
Currently the game works as follows. A standard deck of 52 cards is shuffled and two hands of seven cards are dealt. The next card in the deck is then overturned to work as a "decree" card (to set the trump suit) which is displayed on the right. The bottom hand plays first (leads), and can play any card. The upper hand then plays (follows) subject to the following rules; if there is a card in the hand that matches the suit of the lead card, the follow card must have that suit, otherwise, any card can be played. If the suits match, the higher value wins the trick. If not, the highest value in the trump suit (that of the decree card), if present, wins. Otherwise the lead player wins. The lead card is displayed to the left of the screen on the side of the screen, on top if it comes from the top hand, and bottom if it comes from the bottom hand. The winner of each turn is currently displayed in the console

# Future plans:
- [ ] Incorporate a way to display the winner of a turn in the window.
- [ ] Add scores for the players.
- [ ] Add a scoreboard or display of finished turns.
- [ ] Finish the game somehow (first to 25 or something).
- [ ] Make it so playing a King lets you change the decree to a hand in your card. Old decree goes to bottom of deck, card from hand gets replaced.
- [ ] Think of other ways to make the game more interesting (add more decks, and other on-play effects, etc)
- [ ] Add option to name players.
- [ ] Use the SFML view class and make a help button.
- [ ] Add a Menu.
- [ ] Lock the screen size so that things don't get broken by resizing.
- [x] Incorporate a bot player so that a user can play against the computer.
- [ ] Make a hint button that highlights playable cards or,
     make playable cards hover slightly when moused over (or both).

# Dreams:
- [ ] Read about the SFML network classes to learn if I could make this a multiplayer game, if so then build it out into a multiplayer game.
- [ ] Make other card games and add them into a menu so there is a choice of games to play.
- [ ] Rewrite the graphics with Qt (becuase that seems to be more popular professionally).
- [ ] Make a port of The Fox in the Forest with two different bots (one trying to win all hands until 6 or 7, and one trying to lose all hands) and see which one wins more. 

