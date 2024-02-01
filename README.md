# xv
single-header pointer/value encryption

pros:
- randomizes the algorithm for each variable to make analysis more difficult
- no external dependencies required
- 
cons:
- uses rand() for key generation and algorithm selection (will be replaced later)


example:
```cpp
struct player_t
{
    xv::xval<float> health;
};

//...

player_t p;
p.health = 1337;

printf("player health (encrypted): %.2f\n", p.health);
printf("player health (decrypted): %.2f\n", p.health.get());
```
