{ pkgs }: {
  deps = [
    pkgs.htop
    pkgs.vim
    pkgs.git
    pkgs.gnumake
    pkgs.gcc
    pkgs.clang_18
    # llvm-profdata and llvm-cov
    pkgs.llvmPackages_18.llvm
    pkgs.libdwarf
    # docs and tidy checks
    pkgs.doxygen
    pkgs.editorconfig-checker
    pkgs.rename
    pkgs.python39
    # web smoke test
    pkgs.nodejs_18
  ];
  env = {
    # emsdk fastcomp binaries dynamically link libxml2
    LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.libxml2 ];
  };
}
