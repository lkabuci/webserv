FROM ubuntu

WORKDIR /mydir

RUN apt-get -y update && apt-get -y install build-essential \
    && apt-get -y install valgrind && apt-get -y install vim

COPY . .

CMD ["bash"]
