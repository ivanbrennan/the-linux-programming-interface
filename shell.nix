{ pkgs ? import <nixpkgs> {} }:

with pkgs; mkShell {
  buildInputs = [ gnumake ];
  shellHook = builtins.readFile ./nix/prompt.sh;
}
