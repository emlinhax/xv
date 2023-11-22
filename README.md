# xv
single-header pointer/value encryption

c++ 17 or higher needed

example:
```cpp
struct player_t
{
    xval<float> health;
};

//...

player_t p;
p.health = 1337;

printf("player health (encrypted): %.2f\n", p.health);
printf("player health (decrypted): %.2f\n", p.health.get());
```
