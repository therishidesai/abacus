{
  description = "A calculator written in C.";

  outputs = { self, nixpkgs }: {
    packages.x86_64-linux.abacus-c =
      let pkgs = import nixpkgs {
            system = "x86_64-linux";
          };
          stdenv = pkgs.clangStdenv;
      in stdenv.mkDerivation {
        pname = "abacus-c";
        version = "1.0.0";
        src = ./.;

        # unpackPhase = ''
        #             ls -la $src
        # '';

        buildPhase = ''
                   ls -la
                   make
        '';

        installPhase = ''
                     mkdir -p $out/bin
                     cp abacus-c $out/bin/.
        '';
      };

    # Specify the default package
    defaultPackage.x86_64-linux = self.packages.x86_64-linux.abacus-c;
  };
}
