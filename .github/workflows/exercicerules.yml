name: sysinfo CI
on: 
  push:
    branches:
      - 'feature/**'
    tags:
      - 'v*.*.*'

jobs:
    C-lint-sysinfo:
      if: startsWith(github.ref, 'refs/heads/feature/')
      runs-on: ubuntu-latest
      steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: sysinfo lint
              run: make lint
              
    C-compilation-sysinfo:
        if: startsWith(github.ref, 'refs/heads/feature/') || startsWith(github.ref, 'refs/tags/v')
        runs-on: ubuntu-latest
        permissions:
          id-token: write
          contents: read
          attestations: write 
        needs: C-lint-sysinfo
        steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: sysinfo compilation
              run: make build
            - name: Generate attestation
              uses: actions/attest-build-provenance@v1
              with:
                subject-path: 'sysinfo'
            - name: sysinfo upload artifacts
              uses: actions/upload-artifact@v4
              with:
                path: sysinfo
                name: sysinfo-${{ github.sha }}              
    
    C-run-sysinfo:
        if: startsWith(github.ref, 'refs/heads/feature/')
        runs-on: ubuntu-latest
        needs: C-compilation-sysinfo
        steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: sysinfo download artifacts
              uses: actions/download-artifact@v6
              with:
                name: sysinfo-${{ github.sha}}
            - name: run sysinfo
              run: |
                 chmod +x sysinfo
                 ./sysinfo
                 
    Py-lint-mysystem:
        if: startsWith(github.ref, 'refs/heads/feature/')
        runs-on: ubuntu-latest
        steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: Python environment
              uses: actions/setup-python@v5
              with:
                python-version: 3.12
            - name: lint verification
              run: |
                pip install ifaddr psutil pylint
                pylint --disable=missing-docstring script/mysystem/mysystem.py
                
    Py-run-mysystem:
        if: startsWith(github.ref, 'refs/heads/feature/')
        runs-on: ubuntu-latest
        needs: Py-lint-mysystem   
        steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: Python environment
              uses: actions/setup-python@v5
              with:
                python-version: 3.12
            - name: run script
              run: |
                pip install ifaddr psutil 
                python script/mysystem/mysystem.py
                
    deploy-release:
        if: startsWith(github.ref, 'refs/tags/v')
        runs-on: ubuntu-latest
        needs: C-compilation-sysinfo
        permissions:
          contents: write
          packages: write
        steps:
            - name: sysinfo checkout
              uses: actions/checkout@v6
            - name: sysinfo download artifacts
              uses: actions/download-artifact@v6
              with:
                name: sysinfo-${{ github.sha }}
            - name: Create Release
              uses: softprops/action-gh-release@v2
              with:
                files: sysinfo
                draft: false
