# Building the TAMPL documentation locally

To generate the HTML documentation site, follow these steps:

1. Ensure you are inside a virtual environment. If not, create one and install the necessary dependencies:
   ```bash
   pip install -r requirements.txt
   ```

2. Navigate to the `docs` folder and build the documentation by running:
   ```bash
   make html
   ```

3. The HTML files will be generated in the `_build/html` directory. Open the `index.html` file in this directory using your browser to view the documentation site.