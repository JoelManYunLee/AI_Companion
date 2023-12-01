# This assumes the container is running on a system with a CUDA GPU
FROM tensorflow/tensorflow:latest-gpu

#Copy the requirements file and install dependencies
COPY requirements.txt /tf-knugs/requirements.txt
WORKDIR /tf-knugs
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application code
COPY ./tf-knugs

# Expose the port for jupyter lab
EXPOSE 8888

ENTRYPOINT ["jupyter", "lab","--ip=0.0.0.0","--allow-root","--no-browser"]