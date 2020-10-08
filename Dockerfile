FROM mmore500/conduit

USER root

COPY . /opt/signalgp-lite

# Define default working directory.
WORKDIR /opt/signalgp-lite
