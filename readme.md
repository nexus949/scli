# Shortcut Command Line Interface (SCLI)

![Static Badge](https://img.shields.io/badge/C%2B%2B-%2300599C?style=for-the-badge&logo=cplusplus&logoColor=%23FFFFFF)

SCLI is a simple command line application to open paths with just one command no matter how nested it is.

SCLI is Windows only at least for now...

---

### 📥 Download

1. Download scli from [here](https://github.com/nexus949/scli/releases/download/v1.0/scli.exe).

2. Add the path to the downloaded binary in environment variables and you are good to go.

3. Open cmd or powershell and type `scli help` to get the list of commands.

---

### 🔨 Building from Source

*[ NOTE ]* To build from source you will need **C++17** or above.

1. Clone the repository and navigate into the directory.

```shell
git clone https://github.com/nexus949/scli.git && cd scli
```

2. Build using `g++`. This will generate the binary !

```shell
g++ ./binaries/* -o scli
```

3. Add the path to the downloaded binary in environment variables and you are good to go.
 
4. Open cmd or powershell and type `scli help` to get the list of commands.

---

### ❓ How does it work ?

scli uses terminal arguments using `argc` and `argv[]` to get commands. It then parses them and then stores them in a simple text file (`.txt`).

scli stores keys and path in a key - value pair structure and read from the that file itself. Example : `dwn="C://users/username/donwloads"`. And then open using `scli open dwn`. (The key `dwn` must match what is stored in the `.txt` file !).

Strict parsing rules have been applied so that any tampering or misalignment with the structure will cause scli to throw error.

**AS LONG AS ONE STICKS TO COMMANDS ALL WILL BE GOOD**

Each key value - pair must be unique ! If duplicates are entered manually by editing the `.txt` file then scli will throw error !

While opening, scli checks if a stored path associated with the key is valid or not, and if valid it will open it.

**SCLI CANNOT OPEN FILES THAT REQUIRE ADMINISTRATOR PREMISSION**

(I am using `std::system()` for opening directories and files, I tried using `ShellExecuteA()` with `runas` but still it prompts for permission and upon hitting yes the application just remains in the task manager and not open.)

---

### ❗ Why Even make this in the first Place ?

I found myself jumping back and forth between folders a lot and that was the perfect excuse to make my first ever C++ application and its cool...😁

---

### ℹ Additional Information

- SCLI was compiled using C++17.
- AI tools used - ChatGPT and Microsoft Copilot.
- Its currently Windows Only but I think only changing the system call will allow to make versions for Linux and MacOS too.
- I am open to improvements, suggestions and Feedback !
