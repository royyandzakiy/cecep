# DEVELOPMENT

- fix wierd ftxui dropdown selection

---

```bash
ccp setup
ccp projectname normal/full/min/lib/qml
ccp lib/l list/add/rem name
ccp tool/t list/install/run name
- clang tidy
ccp cbrm (clean, build, run, run multiple) presetname
ccp harden list/run
- lists all hardening tools (sanitizers), their availability, the cmake options status ON/OFF
ccp ai context/tree/adr/readme
```

notes:

- when selection like tool,presetname, can press up down to select
- use toml to enable pckg mgr agnostic (storing library names/versions)
