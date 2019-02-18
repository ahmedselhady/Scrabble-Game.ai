

# Contributing to Scrabble-Game repository

First of all, allow us to thank you from all our hearts for taking time to read this before contributing!

Before we get started, please be aware that you will not be able to push code directly to the master branch. This is to ensure that the master branch contains commits that represent only accepted working states of the game. Thus, the only way for master to change is via merge commits, or emergency administrator commits.

As such, you **must** write your code in separate branches and then integrate your changes via a pull request.

You should adhere to code of conduct specified in this document. Only accepted working branches will be merged to master branch. Feel free to fix any violations and re-commit your work.

# Creating Development Branches
It is very important for you to be aware of the branch you are working on, when writing code. After setting up this repository on your machine, make sure that you create, if needed, and work on the **appropriate branch**.

# Branch Naming
Your branches should adhere to the following scheme, in order to reduce confusion.

    <project name>-<branch description>/<feature>
where:
<project name> describes your project (ex. GUI, DOC, TEST) must be in **uppercase letters**.
<branch description> is a short but **meaningful** description of what is being worked on in the branch, must be in all **lowercase letters**
<feature> (optional feild) is a short meaningful name of the specific feature in your project to which this brach is dedicated,  must be in all **lowercase letters**.

Notice: for all tags, substitute the whitespaces with hyphen character, as it's the convention in Github. 
    ```
    eg. "This Sentence Should Look Like This" ==> "This-Sentence-Should-Look-Like-This" 
    ```


Please try your best to **adhere to a single** <project name> when creating multiple branches.

 Please Notice: **It is acceptable to have and work on only a single branch, named after your project.**
 There is no pressure to partition multiple types of changes over multiple branches, as long as you believe it will not be confusing to review and eventually merge.

**Do**
  - LOGGER
  - GUI-initial-screens-and-game/welcome-screen
  - GUI-player-screens-and-gameplay/pause-screen
  - TEST-block-testing/gui-test-cases

**Don't**
  - add-welcome-screen
  - gui-all

# Branch Souce
Your new branch **should** originate from the latest commit in master. However, this is not a strict rule; if you feel it would ease development, you could branch off any commit in a dev branch.

Ideally, you would **pull** your source branch's latest changes **before** branching.

The commands you could run to achieve this are:

    git checkout master
    git pull
    git checkout -b <name>

where <name> is your new branch's name.

# Commits Format
On Committing to your branch, you must include a commit message describing changes you added in this commit. The message format **must** adhere to the following scheme.

The message is expected to be as follows:
```
Summarize changes in around 50 characters or less
<leave a blank line>
More detailed explanatory text, if necessary. Wrap it to about 72
characters or so. In some contexts, the first line is treated as the
subject of the commit and the rest of the text as the body. The
blank line separating the summary from the body is critical (unless
you omit the body entirely); various tools like `log`, `shortlog`
and `rebase` can get confused if you run the two together.

Explain the problem that this commit is solving. Focus on why you
are making this change as opposed to how (the code explains that).
Are there side effects or other unintuitive consequences of this
change? Here's the place to explain them.

Further paragraphs come after blank lines. (if nessesary)

 - Bullet points are okay, too
 - Typically a hyphen or asterisk is used for the bullet, preceded
   by a single space
   
if more than a developer is commiting to the same branch, you should add the following:
@Author: <your full name> ,where in full name must capitalize the initials, of course.
```
Commits that have empty messages or messages that fail to follow the scheme will be **discarded** and **deleted** from branch.

# File Naming
You are expected to provide meaningful file names. Unless the files should be named according to some convention, you should adhere to the following scheme:

    <file name>.<extension>
where:
<file name> is a meaningful name of medium length, following [Pascal Case] naming convention
<extension> is the extension of this file

# Classes and Variables Naming

Since the project has more than a module, and some modules may use different programming languages than others; the classes and variables naming convention will depend on the language you use. Each Language convention will be **linted separately** to make sure its naming conventions are consistent.

However, there are certain general rules you **must** follow, whatever language you are using:
  - All Names Should be **NON Atomic**. e.g: you **CANNOT** use an iterator "i" in loops, use meaningful name otherwise
  - Indentaions **MUST** be reasonable and consistent with layers of code.
  - Comments should be present in plain **English** language.For now, no other language is accepted, specifically **Franko-Arab** shall **NEVER** be tolerated 
  - TODOs should be written in code, as well as any important annotations that you see valiable, do not hezitate to write them down

It is **recommended** that you read the best practices of the language you use before implementing your work into code.

You can find useful links for some languages here:
* [Python] - Best Practices
* [C++] - Best Practices 
* [C#] - Best Practices as specified by Microsoft
### Technologies we use
To be announced later :D 
### TODOs
 To be announced later :D

This document is adapted from MIT [MY18] Repository

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [scrabble-game]: <https://github.com/AhmedSalemElhady/Scrabble-Game.ai>
   [MY18]: <https://github.com/MITMotorsports/MY18>
   [Pascal Case]: <https://www.quora.com/What-is-the-difference-between-Pascal-Case-and-Camel-Case>
   [Camel Case]: <https://www.quora.com/What-is-the-difference-between-Pascal-Case-and-Camel-Case>
   [Python]: <https://www.python.org/dev/peps/pep-0008/>
   [C++]: <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md>
   [C#]: <https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/inside-a-program/coding-conventions>
   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>

