# Incredible game

## Rough description
This game is very incredible indeed. The player goes through a linear sequence of locations each boasting an incredible minigame (hence the name). No matter if he wins or loses he will hear a location appropriate rowdy banter or calming descriptions of nature, all __decorated__ (get it?) with some incredible text effects.

## Used design patterns

### Singleton / Facade
IOManager class is a singleton, but also a facade. It enables the programmer (me) to easily format messages without paying attention to how they are rendered.

### Strategy 1.
IOEnvironment takes in a preformatted message and displays it using the local system's formatting.

### Decorator
ParseDecorator interface makes it easy to add or remove formatting options. If I ever find it necessary to add a new effect to the text I output, I can do that in a jiffy!

### Chain of responsibility
Event is an interface of an element of a chain of responsibility! It's container is EventChain. It makes it easy to string together a multitude of different Events in any order whatsoever!

### Template method and Strategy 2.
Thanks to the use of these patterns it's very easy to mix and match different location-specific ambiental flavour texts with each minigame, and doesn't require any additional effort while adding a new game or a location!
