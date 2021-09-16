FROM mmore500/conduit@sha256:8fdf051fb36163216e85bd0f162070a2224b2736874eee48bdd6fa1ace5efc99

USER root

COPY . /opt/signalgp-lite

RUN \
  pip3 install -r /opt/signalgp-lite/docs/requirements.txt \
    && \
  echo "installed documentation build requirements"

# make sure unprivileged user has access to new files in opt
# adapted from https://stackoverflow.com/a/27703359
# and https://superuser.com/a/235398
RUN \
  chgrp --recursive user /opt/signalgp-lite \
    && \
  chmod --recursive g+rwx /opt/signalgp-lite \
    && \
  echo "user granted permissions to /opt/signalgp-lite"

USER user

# Define default working directory.
WORKDIR /opt/signalgp-lite

RUN \
  make install-test-dependencies \
    && \
  echo "installed test dependencies"
