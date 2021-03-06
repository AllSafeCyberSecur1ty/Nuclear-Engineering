import sys
import os.path
import re
import time
from docutils import io, nodes, statemachine, utils

try:
    from docutils.utils.error_reporting import ErrorString  # the new way
except ImportError:
    from docutils.error_reporting import ErrorString  # the old way
from docutils.parsers.rst import Directive, convert_directive_function
from docutils.parsers.rst import directives, roles, states
from docutils.parsers.rst.roles import set_classes
from docutils.transforms import misc

from nbconvert import HTMLExporter


class Notebook(Directive):
    """Use nbconvert to insert a notebook into the environment.
    This is based on the Raw directive in docutils
    """

    required_arguments = 1
    optional_arguments = 0
    final_argument_whitespace = True
    option_spec = {}
    has_content = False

    def run(self):
        # check if raw html is supported
        if not self.state.document.settings.raw_enabled:
            raise self.warning('"%s" directive disabled.' % self.name)

        # set up encoding
        attributes = {"format": "html"}
        encoding = self.options.get(
            "encoding", self.state.document.settings.input_encoding
        )
        e_handler = self.state.document.settings.input_encoding_error_handler

        # get path to notebook
        source_dir = os.path.dirname(
            os.path.abspath(self.state.document.current_source)
        )
        nb_path = os.path.normpath(os.path.join(source_dir, self.arguments[0]))
        nb_path = utils.relative_path(None, nb_path)

        # convert notebook to html
        exporter = HTMLExporter(template_file="full")
        output, resources = exporter.from_filename(nb_path)
        header = output.split("<head>", 1)[1].split("</head>", 1)[0]
        body = output.split("<body>", 1)[1].split("</body>", 1)[0]

        # add HTML5 scoped attribute to header style tags
        header = header.replace("<style", '<style scoped="scoped"')
        header = header.replace("body{background-color:#ffffff;}\n", "")
        header = header.replace(
            "body{background-color:white;position:absolute;"
            "left:0px;right:0px;top:0px;bottom:0px;"
            "overflow:visible;}\n",
            "",
        )
        header = header.replace("background-color:#ffffff;", "", 1)

        # concatenate raw html lines
        lines = ['<div class="ipynotebook">']
        lines.append(header)
        lines.append(body)
        lines.append("</div>")
        text = "\n".join(lines)

        # add dependency
        self.state.document.settings.record_dependencies.add(nb_path)
        attributes["source"] = nb_path

        # create notebook node
        nb_node = notebook("", text, **attributes)
        (nb_node.source, nb_node.line) = self.state_machine.get_source_and_line(
            self.lineno
        )

        return [nb_node]


class notebook(nodes.raw):
    pass


def visit_notebook_node(self, node):
    self.visit_raw(node)


def depart_notebook_node(self, node):
    self.depart_raw(node)


def setup(app):
    app.add_node(notebook, html=(visit_notebook_node, depart_notebook_node))

    app.add_directive("notebook", Notebook)
