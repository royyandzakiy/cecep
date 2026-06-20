# DEVELOPMENT

- prjctname as opt
  - changes @prjctname@
  - set @CPP_VERSION@
- remove .git, call git init
- create cpp min
  - add ccp min
  -vadd cpp qml
- create lib list > ccp can printout and add
  - chabge gtest as vcpkg, no fetch content pls

---

```bash
ccp setup
ccp projectname -m normal/full/min/lib/qml
ccp lib/-l list/add/rem name
ccp tool/-t list/install/run name
- profilers
ccp cbrm (clean, build, run, run multiple) presetname (skip)
ccp harden list/run
- lists all hardening tools (sanitizers), their availability, the cmake options status ON/OFF
ccp ai context/tree/adr/readme
```

notes:

- when selection like tool,presetname, can press up down to select
- retains selection history, as listed
- use toml to enable pckg mgr agnostic (storing library names/versions)