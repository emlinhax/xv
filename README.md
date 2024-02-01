# xv
single-header pointer/value encryption

- randomizes the algorithm for each variable so it never looks the same
- no external dependencies required

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
