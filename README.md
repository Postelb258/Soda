<div  align="center"><h1>Soda🥤</h1></div>

![License](https://img.shields.io/github/license/Postelb258/Soda.svg?style=flat) ![Commit Activity](https://img.shields.io/github/commit-activity/w/Postelb258/Soda) ![Version](https://img.shields.io/badge/version-0.1.0-blue)

## Introduction

**Soda** is a new gen C/C++ package manager that will bring you the experience of `npm`, `pip` or `cargo` ease of running, building, linking, testing, getting packages and so on. The main pillar of **Soda** - extendability dictates an ability to add aliases, control pipeline with TOML config and powerful CLI but also add your own variety of compilers and commands to CLI supported by API.

## Getting Started

...

## Overview

As you installed the **Soda** executable, you can use it to create a project by:

```bash

soda new PATH

```

It will create at PATH the C project with binary template. To change the language use flag `--cxx` and for library template `-l` or `--lib`.

For path in current directory use dot.

To build and link project, go to project directory and run

```console

soda build

```

By default it will build and link in debug mode, but specifying `-r` or `--release` you can change it.

...

## To Devs⚙️

Those who want to contribute into the project by fixing, extending the project you can create a pull request referring to [Dev GitBook]().

## Dependencies

The external dependencies are:

-   [TOML Parser](https://github.com/ToruNiina/toml11)

-   [CLI Parser](https://github.com/CLIUtils/CLI11)
