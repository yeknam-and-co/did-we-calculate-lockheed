# math checker thingy

yo this thing checks if ur math is right. made it for some lockheed thing but honestly its pretty useful for when u need to check if ur not being dumb with numbers

## what it do

- takes ur equations and tells u if ur smart or not
- does all the basic stuff:
  - adding (cuz sometimes 2+2=5)
  - subtracting (when ur not sure if u have enough money)
  - multiplying (for when u need to flex ur calculator skills)
  - dividing (but it wont let u divide by zero cuz thats just rude)
  - powers (for when u need to calculate how many times u failed at math)
  - square roots (cuz sometimes u need to find the root of ur problems)
  - parentheses (for when u need to group ur existential crisis)

## how to make it work

```bash
# if ur using clang (the cool kids compiler) because i used mac
clang++ -std=c++17 -O2 -Wall -Wextra -pedantic -o main main.cpp

# if ur using gcc (the other compiler)
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o main main.cpp
```

## how to use it (its not rocket science)

1. run it:
```bash
./main
```

2. give it some equations like:
```
2
2+2=5  # spoiler: this is wrong
sqrt(16)=4  # this ones actually right, good job!
```

## what it can handle

- first line: how many equations u want to check (dont go crazy now)
- then just throw equations at it like: `ur_math = ur_guess`
- its pretty smart (unlike some of us):
  - decimals (for when u need to be precise about ur mistakes)
  - spaces (it ignores them, just like it ignores ur bad math)
  - square roots (for finding the root of ur problems)
  - parentheses (for when u need to group ur thoughts)
  - all the basic math stuff (cuz sometimes u need a second opinion)

## heres an example (cuz we all need one)

u give it:
```
3
2+2=5  # classic mistake
sqrt(16)=4  # finally, something right
5*3=14  # math is hard, ok?
```

it tells u:
```
4  # "actually, its 4, u absolute donut"
correct  # "u got one right, proud of u"
15  # "nope, try again champ"
```
## fun facts

- its pretty good with decimals (unlike my ex)
- itll tell u if u messed up (like a good friend should)
- it wont let u divide by zero (cuz thats just mean)
- no fancy error messages (we keep it real here)

## found a bug?

pull requests welcome! or just tell me about it and ill probably fix it when i feel like it

p.s. if ur reading this, u probably need to check ur math. its ok, weve all been there 😉 

made with love by ian t,

this readme was not if theres misinformation blame cursor for making this thx
contact discord:yeknampogo if you got issues
<3