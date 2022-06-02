#!/usr/bin/env groovy
// Declarative //
pipeline {
	agent any

	stages {
		stage ('Build') {
			steps {
				sh 'cd Hindsight && ./gradlew build'
				archiveArtifacts artifacts: 'Hindsight/build/exe/frcUserProgram/debug/frcUserProgram'
			}
		}

		stage('Test') {
			steps {
				echo 'Make some tests, please!'

				/*
				script {
					try {
						// do tests
					}
					catch (ex) {
						currentBuild.result = 'UNSTABLE'
					}
				}
				*/
			}
		}
	}
}
