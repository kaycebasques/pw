# pw

(╯°□°)╯︵ ┻━┻

## Targets

### Bare-metal targets

`pw_executable`

#### `host_bare`

```
./out/host_bare_debug/obj/src/bin/hello_world_bare
```

### `pw_system` targets

`pw_system_target`

#### `host_sys`

## Console

```
./out/hostsys.debug/obj/src/bin/hello_world & pw-system-console -s default --proto-globs third_party/pigweed/pw_rpc/echo.proto && killall hello_world
```
