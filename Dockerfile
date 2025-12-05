FROM python:3.11-slim
RUN mkdir -p /app/script/mysystem
COPY sysinfo /app/sysinfo
COPY script/mysystem/mysystem.py /app/script/mysystem/mysystem.py
RUN chmod +x /app/sysinfo

WORKDIR /app

CMD ["bash"]
