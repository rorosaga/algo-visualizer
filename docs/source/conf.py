import os

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = "ALGO-VISUALIZER"
copyright = "2024, RAMCAV, ROXANNE, YOUNG JOSEPH, NARUTO TABOADA"
author = "RAMCAV, ROXANNE, YOUNG JOSEPH, NARUTO TABOADA"

# -- Breathe Configuration ---------------------------------------------------
breathe_projects = {
    "ALGO-VISUALIZER": os.path.join(os.path.dirname(__file__), "../../build/docs/doxygen/xml")
}

breathe_default_project = "ALGO-VISUALIZER"


# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration
primary_domain = "cpp"
extensions = ["breathe"]

# Breathe Configuration
breathe_default_project = project
templates_path = ["_templates"]
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "sphinx_rtd_theme"
html_static_path = ["_static"]
