FROM python:3.11-slim
RUN mkdir -p /app/bin /app/script/mysystem
COPY bin/sysinfo /app/bin/sysinfo
COPY script/mysystem/mysystem.py /app/script/mysystem/mysystem.py
RUN chmod +x /app/bin/sysinfo

ENV PATH="/app/bin:$PATH"
WORKDIR /app

CMD ["bash"]
